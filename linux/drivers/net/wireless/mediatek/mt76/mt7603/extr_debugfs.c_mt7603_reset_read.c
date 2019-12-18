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
struct mt7603_dev {int /*<<< orphan*/ * reset_cause; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
#define  RESET_CAUSE_BEACON_STUCK 134 
#define  RESET_CAUSE_MCU_HANG 133 
#define  RESET_CAUSE_RESET_FAILED 132 
#define  RESET_CAUSE_RX_BUSY 131 
#define  RESET_CAUSE_RX_PSE_BUSY 130 
#define  RESET_CAUSE_TX_BUSY 129 
#define  RESET_CAUSE_TX_HANG 128 
 struct mt7603_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7603_reset_read(struct seq_file *s, void *data)
{
	struct mt7603_dev *dev = dev_get_drvdata(s->private);
	static const char * const reset_cause_str[] = {
		[RESET_CAUSE_TX_HANG] = "TX hang",
		[RESET_CAUSE_TX_BUSY] = "TX DMA busy stuck",
		[RESET_CAUSE_RX_BUSY] = "RX DMA busy stuck",
		[RESET_CAUSE_RX_PSE_BUSY] = "RX PSE busy stuck",
		[RESET_CAUSE_BEACON_STUCK] = "Beacon stuck",
		[RESET_CAUSE_MCU_HANG] = "MCU hang",
		[RESET_CAUSE_RESET_FAILED] = "PSE reset failed",
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(reset_cause_str); i++) {
		if (!reset_cause_str[i])
			continue;

		seq_printf(s, "%20s: %u\n", reset_cause_str[i],
			   dev->reset_cause[i]);
	}

	return 0;
}