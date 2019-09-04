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
struct omap_sham_dev {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_FINAL ; 
 int /*<<< orphan*/  SHA_REG_CTRL ; 
 int /*<<< orphan*/  SHA_REG_CTRL_LENGTH ; 
 int /*<<< orphan*/  SHA_REG_CTRL_OUTPUT_READY ; 
 int /*<<< orphan*/  omap_sham_irq_common (struct omap_sham_dev*) ; 
 int /*<<< orphan*/  omap_sham_read (struct omap_sham_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_sham_write_mask (struct omap_sham_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t omap_sham_irq_omap2(int irq, void *dev_id)
{
	struct omap_sham_dev *dd = dev_id;

	if (unlikely(test_bit(FLAGS_FINAL, &dd->flags)))
		/* final -> allow device to go to power-saving mode */
		omap_sham_write_mask(dd, SHA_REG_CTRL, 0, SHA_REG_CTRL_LENGTH);

	omap_sham_write_mask(dd, SHA_REG_CTRL, SHA_REG_CTRL_OUTPUT_READY,
				 SHA_REG_CTRL_OUTPUT_READY);
	omap_sham_read(dd, SHA_REG_CTRL);

	return omap_sham_irq_common(dd);
}