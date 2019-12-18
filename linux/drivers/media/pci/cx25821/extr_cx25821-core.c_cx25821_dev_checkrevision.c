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
struct cx25821_dev {int hwrevision; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDR_CFG2 ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static void cx25821_dev_checkrevision(struct cx25821_dev *dev)
{
	dev->hwrevision = cx_read(RDR_CFG2) & 0xff;

	pr_info("Hardware revision = 0x%02x\n", dev->hwrevision);
}