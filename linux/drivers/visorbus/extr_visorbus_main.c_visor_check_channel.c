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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct channel_header {scalar_t__ size; scalar_t__ version_id; scalar_t__ signature; int /*<<< orphan*/  chtype; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  guid_is_null (int /*<<< orphan*/  const*) ; 

int visor_check_channel(struct channel_header *ch, struct device *dev,
			const guid_t *expected_guid, char *chname,
			u64 expected_min_bytes, u32 expected_version,
			u64 expected_signature)
{
	if (!guid_is_null(expected_guid)) {
		/* caller wants us to verify type GUID */
		if (!guid_equal(&ch->chtype, expected_guid)) {
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=type expected=%pUL actual=%pUL\n",
				chname, expected_guid, expected_guid,
				&ch->chtype);
			return 0;
		}
	}
	/* verify channel size */
	if (expected_min_bytes > 0) {
		if (ch->size < expected_min_bytes) {
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=size expected=0x%-8.8Lx actual=0x%-8.8Lx\n",
				chname, expected_guid,
				(unsigned long long)expected_min_bytes,
				ch->size);
			return 0;
		}
	}
	/* verify channel version */
	if (expected_version > 0) {
		if (ch->version_id != expected_version) {
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=version expected=0x%-8.8lx actual=0x%-8.8x\n",
				chname, expected_guid,
				(unsigned long)expected_version,
				ch->version_id);
			return 0;
		}
	}
	/* verify channel signature */
	if (expected_signature > 0) {
		if (ch->signature != expected_signature) {
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=signature expected=0x%-8.8Lx actual=0x%-8.8Lx\n",
				chname, expected_guid,	expected_signature,
				ch->signature);
			return 0;
		}
	}
	return 1;
}