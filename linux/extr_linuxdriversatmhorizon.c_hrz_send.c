#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int data; unsigned int len; } ;
struct TYPE_18__ {scalar_t__ traffic_class; unsigned int max_sdu; } ;
struct TYPE_19__ {TYPE_1__ txtp; } ;
struct atm_vcc {TYPE_2__ qos; int /*<<< orphan*/  dev; } ;
struct TYPE_20__ {scalar_t__ channel; } ;
typedef  TYPE_3__ hrz_vcc ;
struct TYPE_21__ {scalar_t__ last_vc; short tx_last; scalar_t__* tx_channel_record; unsigned int tx_regions; unsigned int tx_bytes; int tx_addr; int /*<<< orphan*/ * tx_iovec; struct sk_buff* tx_skb; } ;
typedef  TYPE_4__ hrz_dev ;
struct TYPE_22__ {unsigned int nr_frags; } ;
struct TYPE_17__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 int ATM_AAL5_TRAILER ; 
 int ATM_CELL_PAYLOAD ; 
 scalar_t__ ATM_NONE ; 
 TYPE_16__* ATM_SKB (struct sk_buff*) ; 
 int DBG_BUS ; 
 int DBG_ERR ; 
 int DBG_FLOW ; 
 int DBG_TX ; 
 int EIO ; 
 int ERESTARTSYS ; 
 TYPE_4__* HRZ_DEV (int /*<<< orphan*/ ) ; 
 TYPE_3__* HRZ_VCC (struct atm_vcc*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SELECT_TX_CHANNEL (TYPE_4__*,short) ; 
 short TX_CHANS ; 
 int /*<<< orphan*/  TX_FREE_BUFFER_COUNT_OFF ; 
 int /*<<< orphan*/  YELLOW_LED_OFF (TYPE_4__*) ; 
 int /*<<< orphan*/  dump_skb (char*,scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  hrz_kfree_skb (struct sk_buff*) ; 
 int rd_regw (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 short setup_idle_tx_channel (TYPE_4__*,TYPE_3__*) ; 
 TYPE_8__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ tx_hold (TYPE_4__*) ; 
 int /*<<< orphan*/  tx_release (TYPE_4__*) ; 
 int /*<<< orphan*/  tx_schedule (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hrz_send (struct atm_vcc * atm_vcc, struct sk_buff * skb) {
  unsigned int spin_count;
  int free_buffers;
  hrz_dev * dev = HRZ_DEV(atm_vcc->dev);
  hrz_vcc * vcc = HRZ_VCC(atm_vcc);
  u16 channel = vcc->channel;
  
  u32 buffers_required;
  
  /* signed for error return */
  short tx_channel;
  
  PRINTD (DBG_FLOW|DBG_TX, "hrz_send vc %x data %p len %u",
	  channel, skb->data, skb->len);
  
  dump_skb (">>>", channel, skb);
  
  if (atm_vcc->qos.txtp.traffic_class == ATM_NONE) {
    PRINTK (KERN_ERR, "attempt to send on RX-only VC %x", channel);
    hrz_kfree_skb (skb);
    return -EIO;
  }
  
  // don't understand this
  ATM_SKB(skb)->vcc = atm_vcc;
  
  if (skb->len > atm_vcc->qos.txtp.max_sdu) {
    PRINTK (KERN_ERR, "sk_buff length greater than agreed max_sdu, dropping...");
    hrz_kfree_skb (skb);
    return -EIO;
  }
  
  if (!channel) {
    PRINTD (DBG_ERR|DBG_TX, "attempt to transmit on zero (rx_)channel");
    hrz_kfree_skb (skb);
    return -EIO;
  }
  
#if 0
  {
    // where would be a better place for this? housekeeping?
    u16 status;
    pci_read_config_word (dev->pci_dev, PCI_STATUS, &status);
    if (status & PCI_STATUS_REC_MASTER_ABORT) {
      PRINTD (DBG_BUS|DBG_ERR, "Clearing PCI Master Abort (and cleaning up)");
      status &= ~PCI_STATUS_REC_MASTER_ABORT;
      pci_write_config_word (dev->pci_dev, PCI_STATUS, status);
      if (test_bit (tx_busy, &dev->flags)) {
	hrz_kfree_skb (dev->tx_skb);
	tx_release (dev);
      }
    }
  }
#endif
  
#ifdef DEBUG_HORIZON
  /* wey-hey! */
  if (channel == 1023) {
    unsigned int i;
    unsigned short d = 0;
    char * s = skb->data;
    if (*s++ == 'D') {
	for (i = 0; i < 4; ++i)
		d = (d << 4) | hex_to_bin(*s++);
      PRINTK (KERN_INFO, "debug bitmap is now %hx", debug = d);
    }
  }
#endif
  
  // wait until TX is free and grab lock
  if (tx_hold (dev)) {
    hrz_kfree_skb (skb);
    return -ERESTARTSYS;
  }
 
  // Wait for enough space to be available in transmit buffer memory.
  
  // should be number of cells needed + 2 (according to hardware docs)
  // = ((framelen+8)+47) / 48 + 2
  // = (framelen+7) / 48 + 3, hmm... faster to put addition inside XXX
  buffers_required = (skb->len+(ATM_AAL5_TRAILER-1)) / ATM_CELL_PAYLOAD + 3;
  
  // replace with timer and sleep, add dev->tx_buffers_queue (max 1 entry)
  spin_count = 0;
  while ((free_buffers = rd_regw (dev, TX_FREE_BUFFER_COUNT_OFF)) < buffers_required) {
    PRINTD (DBG_TX, "waiting for free TX buffers, got %d of %d",
	    free_buffers, buffers_required);
    // what is the appropriate delay? implement a timeout? (depending on line speed?)
    // mdelay (1);
    // what happens if we kill (current_pid, SIGKILL) ?
    schedule();
    if (++spin_count > 1000) {
      PRINTD (DBG_TX|DBG_ERR, "spun out waiting for tx buffers, got %d of %d",
	      free_buffers, buffers_required);
      tx_release (dev);
      hrz_kfree_skb (skb);
      return -ERESTARTSYS;
    }
  }
  
  // Select a channel to transmit the frame on.
  if (channel == dev->last_vc) {
    PRINTD (DBG_TX, "last vc hack: hit");
    tx_channel = dev->tx_last;
  } else {
    PRINTD (DBG_TX, "last vc hack: miss");
    // Are we currently transmitting this VC on one of the channels?
    for (tx_channel = 0; tx_channel < TX_CHANS; ++tx_channel)
      if (dev->tx_channel_record[tx_channel] == channel) {
	PRINTD (DBG_TX, "vc already on channel: hit");
	break;
      }
    if (tx_channel == TX_CHANS) { 
      PRINTD (DBG_TX, "vc already on channel: miss");
      // Find and set up an idle channel.
      tx_channel = setup_idle_tx_channel (dev, vcc);
      if (tx_channel < 0) {
	PRINTD (DBG_TX|DBG_ERR, "failed to get channel");
	tx_release (dev);
	return tx_channel;
      }
    }
    
    PRINTD (DBG_TX, "got channel");
    SELECT_TX_CHANNEL(dev, tx_channel);
    
    dev->last_vc = channel;
    dev->tx_last = tx_channel;
  }
  
  PRINTD (DBG_TX, "using channel %u", tx_channel);
  
  YELLOW_LED_OFF(dev);
  
  // TX start transfer
  
  {
    unsigned int tx_len = skb->len;
    unsigned int tx_iovcnt = skb_shinfo(skb)->nr_frags;
    // remember this so we can free it later
    dev->tx_skb = skb;
    
    if (tx_iovcnt) {
      // scatter gather transfer
      dev->tx_regions = tx_iovcnt;
      dev->tx_iovec = NULL;		/* @@@ needs rewritten */
      dev->tx_bytes = 0;
      PRINTD (DBG_TX|DBG_BUS, "TX start scatter-gather transfer (iovec %p, len %d)",
	      skb->data, tx_len);
      tx_release (dev);
      hrz_kfree_skb (skb);
      return -EIO;
    } else {
      // simple transfer
      dev->tx_regions = 0;
      dev->tx_iovec = NULL;
      dev->tx_bytes = tx_len;
      dev->tx_addr = skb->data;
      PRINTD (DBG_TX|DBG_BUS, "TX start simple transfer (addr %p, len %d)",
	      skb->data, tx_len);
    }
    
    // and do the business
    tx_schedule (dev, 0);
    
  }
  
  return 0;
}