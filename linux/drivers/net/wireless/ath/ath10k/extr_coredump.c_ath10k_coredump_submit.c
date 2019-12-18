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
struct ath10k_dump_file_data {int /*<<< orphan*/  len; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ath10k_dump_file_data* ath10k_coredump_build (struct ath10k*) ; 
 scalar_t__ ath10k_coredump_mask ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  dev_coredumpv (int /*<<< orphan*/ ,struct ath10k_dump_file_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int ath10k_coredump_submit(struct ath10k *ar)
{
	struct ath10k_dump_file_data *dump;

	if (ath10k_coredump_mask == 0)
		/* coredump disabled */
		return 0;

	dump = ath10k_coredump_build(ar);
	if (!dump) {
		ath10k_warn(ar, "no crash dump data found for devcoredump");
		return -ENODATA;
	}

	dev_coredumpv(ar->dev, dump, le32_to_cpu(dump->len), GFP_KERNEL);

	return 0;
}