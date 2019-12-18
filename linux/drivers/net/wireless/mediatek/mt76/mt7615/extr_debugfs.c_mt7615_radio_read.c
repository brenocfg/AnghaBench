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
struct seq_file {int /*<<< orphan*/  private; } ;
struct mt7615_dev {int /*<<< orphan*/  false_cca_cck; int /*<<< orphan*/  false_cca_ofdm; int /*<<< orphan*/  cck_sensitivity; int /*<<< orphan*/  ofdm_sensitivity; } ;

/* Variables and functions */
 struct mt7615_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7615_radio_read(struct seq_file *s, void *data)
{
	struct mt7615_dev *dev = dev_get_drvdata(s->private);

	seq_printf(s, "Sensitivity: ofdm=%d cck=%d\n",
		   dev->ofdm_sensitivity, dev->cck_sensitivity);
	seq_printf(s, "False CCA: ofdm=%d cck=%d\n",
		   dev->false_cca_ofdm, dev->false_cca_cck);

	return 0;
}