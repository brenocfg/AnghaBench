#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mthca_mtt {int first_seg; } ;
struct mthca_mailbox {scalar_t__* buf; } ;
struct TYPE_4__ {int mtt_seg_size; } ;
struct TYPE_3__ {int mtt_base; } ;
struct mthca_dev {TYPE_2__ limits; TYPE_1__ mr_table; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int MTHCA_MAILBOX_SIZE ; 
 int MTHCA_MTT_FLAG_PRESENT ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 scalar_t__ cpu_to_be64 (int) ; 
 int mthca_WRITE_MTT (struct mthca_dev*,struct mthca_mailbox*,int) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,int) ; 

__attribute__((used)) static int __mthca_write_mtt(struct mthca_dev *dev, struct mthca_mtt *mtt,
			     int start_index, u64 *buffer_list, int list_len)
{
	struct mthca_mailbox *mailbox;
	__be64 *mtt_entry;
	int err = 0;
	int i;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	mtt_entry = mailbox->buf;

	while (list_len > 0) {
		mtt_entry[0] = cpu_to_be64(dev->mr_table.mtt_base +
					   mtt->first_seg * dev->limits.mtt_seg_size +
					   start_index * 8);
		mtt_entry[1] = 0;
		for (i = 0; i < list_len && i < MTHCA_MAILBOX_SIZE / 8 - 2; ++i)
			mtt_entry[i + 2] = cpu_to_be64(buffer_list[i] |
						       MTHCA_MTT_FLAG_PRESENT);

		/*
		 * If we have an odd number of entries to write, add
		 * one more dummy entry for firmware efficiency.
		 */
		if (i & 1)
			mtt_entry[i + 2] = 0;

		err = mthca_WRITE_MTT(dev, mailbox, (i + 1) & ~1);
		if (err) {
			mthca_warn(dev, "WRITE_MTT failed (%d)\n", err);
			goto out;
		}

		list_len    -= i;
		start_index += i;
		buffer_list += i;
	}

out:
	mthca_free_mailbox(dev, mailbox);
	return err;
}