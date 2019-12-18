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
typedef  int u32 ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_FORMAT_CTRL ; 
 int MASK_05 ; 
 int MASK_21 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  calculate_output_format_register (struct saa7146_dev*,unsigned long,int*) ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void saa7146_set_output_format(struct saa7146_dev *dev, unsigned long palette)
{
	u32 clip_format = saa7146_read(dev, CLIP_FORMAT_CTRL);

	/* call helper function */
	calculate_output_format_register(dev,palette,&clip_format);

	/* update the hps registers */
	saa7146_write(dev, CLIP_FORMAT_CTRL, clip_format);
	saa7146_write(dev, MC2, (MASK_05 | MASK_21));
}