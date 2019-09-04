#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atm_dev {int dummy; } ;
typedef  int loff_t ;
struct TYPE_3__ {scalar_t__ phy_type; int pci_map_size; int memType; int num_tx_desc; int tx_buf_sz; int num_rx_desc; int rx_buf_sz; int rx_pkt_cnt; int tx_pkt_cnt; int rx_cell_cnt; int tx_cell_cnt; int drop_rxcell; int drop_rxpkt; } ;
typedef  TYPE_1__ IADEV ;

/* Variables and functions */
 scalar_t__ FE_25MBIT_PHY ; 
 scalar_t__ FE_DS3_PHY ; 
 scalar_t__ FE_E3_PHY ; 
 scalar_t__ FE_UTP_OPTION ; 
 TYPE_1__* INPH_IA_DEV (struct atm_dev*) ; 
 int MEM_SIZE_1M ; 
 int MEM_SIZE_512K ; 
 int MEM_SIZE_MASK ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int ia_proc_read(struct atm_dev *dev,loff_t *pos,char *page)
{ 
  int   left = *pos, n;   
  char  *tmpPtr;
  IADEV *iadev = INPH_IA_DEV(dev);
  if(!left--) {
     if (iadev->phy_type == FE_25MBIT_PHY) {
       n = sprintf(page, "  Board Type         :  Iphase5525-1KVC-128K\n");
       return n;
     }
     if (iadev->phy_type == FE_DS3_PHY)
        n = sprintf(page, "  Board Type         :  Iphase-ATM-DS3");
     else if (iadev->phy_type == FE_E3_PHY)
        n = sprintf(page, "  Board Type         :  Iphase-ATM-E3");
     else if (iadev->phy_type == FE_UTP_OPTION)
         n = sprintf(page, "  Board Type         :  Iphase-ATM-UTP155"); 
     else
        n = sprintf(page, "  Board Type         :  Iphase-ATM-OC3");
     tmpPtr = page + n;
     if (iadev->pci_map_size == 0x40000)
        n += sprintf(tmpPtr, "-1KVC-");
     else
        n += sprintf(tmpPtr, "-4KVC-");  
     tmpPtr = page + n; 
     if ((iadev->memType & MEM_SIZE_MASK) == MEM_SIZE_1M)
        n += sprintf(tmpPtr, "1M  \n");
     else if ((iadev->memType & MEM_SIZE_MASK) == MEM_SIZE_512K)
        n += sprintf(tmpPtr, "512K\n");
     else
       n += sprintf(tmpPtr, "128K\n");
     return n;
  }
  if (!left) {
     return  sprintf(page, "  Number of Tx Buffer:  %u\n"
                           "  Size of Tx Buffer  :  %u\n"
                           "  Number of Rx Buffer:  %u\n"
                           "  Size of Rx Buffer  :  %u\n"
                           "  Packets Received   :  %u\n"
                           "  Packets Transmitted:  %u\n"
                           "  Cells Received     :  %u\n"
                           "  Cells Transmitted  :  %u\n"
                           "  Board Dropped Cells:  %u\n"
                           "  Board Dropped Pkts :  %u\n",
                           iadev->num_tx_desc,  iadev->tx_buf_sz,
                           iadev->num_rx_desc,  iadev->rx_buf_sz,
                           iadev->rx_pkt_cnt,   iadev->tx_pkt_cnt,
                           iadev->rx_cell_cnt, iadev->tx_cell_cnt,
                           iadev->drop_rxcell, iadev->drop_rxpkt);                        
  }
  return 0;
}