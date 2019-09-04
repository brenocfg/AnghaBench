#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  loader_block ;
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ amb_reset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ amb_talk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amb_ucode_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmds ; 
 scalar_t__ create_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_queues (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixup_plx_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_loader_version (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxs ; 
 int /*<<< orphan*/  rxs_bs ; 
 int /*<<< orphan*/  txs ; 
 scalar_t__ ucode_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amb_init(amb_dev *dev)
{
  loader_block lb;
  
  u32 version;
  
  if (amb_reset (dev, 1)) {
    PRINTK (KERN_ERR, "card reset failed!");
  } else {
    fixup_plx_window (dev, &lb);
    
    if (get_loader_version (&lb, dev, &version)) {
      PRINTK (KERN_INFO, "failed to get loader version");
    } else {
      PRINTK (KERN_INFO, "loader version is %08x", version);
      
      if (ucode_init (&lb, dev)) {
	PRINTK (KERN_ERR, "microcode failure");
      } else if (create_queues (dev, cmds, txs, rxs, rxs_bs)) {
	PRINTK (KERN_ERR, "failed to get memory for queues");
      } else {
	
	if (amb_talk (dev)) {
	  PRINTK (KERN_ERR, "adapter did not accept queues");
	} else {
	  
	  amb_ucode_version (dev);
	  return 0;
	  
	} /* amb_talk */
	
	destroy_queues (dev);
      } /* create_queues, ucode_init */
      
      amb_reset (dev, 0);
    } /* get_loader_version */
    
  } /* amb_reset */
  
  return -EINVAL;
}