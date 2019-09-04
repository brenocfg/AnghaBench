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
struct scoop_dev {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCOOP_CCR ; 
 scalar_t__ SCOOP_CDR ; 
 scalar_t__ SCOOP_IMR ; 
 scalar_t__ SCOOP_IRM ; 
 scalar_t__ SCOOP_ISR ; 
 scalar_t__ SCOOP_MCR ; 
 struct scoop_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 

void reset_scoop(struct device *dev)
{
	struct scoop_dev *sdev = dev_get_drvdata(dev);

	iowrite16(0x0100, sdev->base + SCOOP_MCR);  /* 00 */
	iowrite16(0x0000, sdev->base + SCOOP_CDR);  /* 04 */
	iowrite16(0x0000, sdev->base + SCOOP_CCR);  /* 10 */
	iowrite16(0x0000, sdev->base + SCOOP_IMR);  /* 18 */
	iowrite16(0x00FF, sdev->base + SCOOP_IRM);  /* 14 */
	iowrite16(0x0000, sdev->base + SCOOP_ISR);  /* 1C */
	iowrite16(0x0000, sdev->base + SCOOP_IRM);
}