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
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_22 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  saa7146_disable_clipping (struct saa7146_dev*) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void saa7146_disable_overlay(struct saa7146_fh *fh)
{
	struct saa7146_dev *dev = fh->dev;

	/* disable clipping + video dma1 */
	saa7146_disable_clipping(dev);
	saa7146_write(dev, MC1, MASK_22);
}