#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; scalar_t__* sense_buffer; } ;
struct atp_unit {unsigned int* active_id; size_t* quend; size_t* quhd; scalar_t__* in_int; scalar_t__* in_snd; int /*<<< orphan*/ * ioport; struct scsi_cmnd*** quereq; } ;
struct Scsi_Host {int /*<<< orphan*/  hostdata; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 scalar_t__ atp_readb_io (struct atp_unit*,unsigned char,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 size_t qcnt ; 
 int scmd_channel (struct scsi_cmnd*) ; 
 unsigned int scmd_id (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_s870 (struct atp_unit*,unsigned char) ; 

__attribute__((used)) static int atp870u_queuecommand_lck(struct scsi_cmnd *req_p,
			 void (*done) (struct scsi_cmnd *))
{
	unsigned char c;
	unsigned int m;
	struct atp_unit *dev;
	struct Scsi_Host *host;

	c = scmd_channel(req_p);
	req_p->sense_buffer[0]=0;
	scsi_set_resid(req_p, 0);
	if (scmd_channel(req_p) > 1) {
		req_p->result = 0x00040000;
		done(req_p);
#ifdef ED_DBGP		
		printk("atp870u_queuecommand : req_p->device->channel > 1\n");	
#endif			
		return 0;
	}

	host = req_p->device->host;
	dev = (struct atp_unit *)&host->hostdata;
		

		
	m = 1;
	m = m << scmd_id(req_p);

	/*
	 *      Fake a timeout for missing targets
	 */

	if ((m & dev->active_id[c]) == 0) {
		req_p->result = 0x00040000;
		done(req_p);
		return 0;
	}

	if (done) {
		req_p->scsi_done = done;
	} else {
#ifdef ED_DBGP		
		printk( "atp870u_queuecommand: done can't be NULL\n");
#endif		
		req_p->result = 0;
		done(req_p);
		return 0;
	}
	
	/*
	 *	Count new command
	 */
	dev->quend[c]++;
	if (dev->quend[c] >= qcnt) {
		dev->quend[c] = 0;
	}
	
	/*
	 *	Check queue state
	 */
	if (dev->quhd[c] == dev->quend[c]) {
		if (dev->quend[c] == 0) {
			dev->quend[c] = qcnt;
		}
#ifdef ED_DBGP		
		printk("atp870u_queuecommand : dev->quhd[c] == dev->quend[c]\n");
#endif		
		dev->quend[c]--;
		req_p->result = 0x00020000;
		done(req_p);	
		return 0;
	}
	dev->quereq[c][dev->quend[c]] = req_p;
#ifdef ED_DBGP	
	printk("dev->ioport[c] = %x atp_readb_io(dev, c, 0x1c) = %x dev->in_int[%d] = %d dev->in_snd[%d] = %d\n",dev->ioport[c],atp_readb_io(dev, c, 0x1c),c,dev->in_int[c],c,dev->in_snd[c]);
#endif
	if ((atp_readb_io(dev, c, 0x1c) == 0) && (dev->in_int[c] == 0) && (dev->in_snd[c] == 0)) {
#ifdef ED_DBGP
		printk("Call sent_s870(atp870u_queuecommand)\n");
#endif		
		send_s870(dev,c);
	}
#ifdef ED_DBGP	
	printk("atp870u_queuecommand : exit\n");
#endif	
	return 0;
}