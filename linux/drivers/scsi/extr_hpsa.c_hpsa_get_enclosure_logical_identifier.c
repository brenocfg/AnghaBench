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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RECEIVE_DIAGNOSTIC ; 
 int /*<<< orphan*/  get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int hpsa_do_receive_diagnostic (struct ctlr_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 hpsa_get_enclosure_logical_identifier(struct ctlr_info *h,
						u8 *scsi3addr)
{
	u8 *buf;
	u64 sa = 0;
	int rc = 0;

	buf = kzalloc(1024, GFP_KERNEL);
	if (!buf)
		return 0;

	rc = hpsa_do_receive_diagnostic(h, scsi3addr, RECEIVE_DIAGNOSTIC,
					buf, 1024);

	if (rc)
		goto out;

	sa = get_unaligned_be64(buf+12);

out:
	kfree(buf);
	return sa;
}