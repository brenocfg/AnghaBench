#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct parsed_partitions {int dummy; } ;
struct TYPE_2__ {int vblk_size; int vblk_offset; int last_vblk_seq; } ;
struct ldmdb {TYPE_1__ vm; } ;
typedef  int /*<<< orphan*/  Sector ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ MAGIC_VBLK ; 
 scalar_t__ OFF_VMDB ; 
 int /*<<< orphan*/  frags ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldm_crit (char*) ; 
 int /*<<< orphan*/  ldm_error (char*) ; 
 int /*<<< orphan*/  ldm_frag_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int ldm_frag_commit (int /*<<< orphan*/ *,struct ldmdb*) ; 
 int /*<<< orphan*/  ldm_frag_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldm_ldmdb_add (int /*<<< orphan*/ *,int,struct ldmdb*) ; 
 int /*<<< orphan*/  put_dev_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_part_sector (struct parsed_partitions*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ldm_get_vblks(struct parsed_partitions *state, unsigned long base,
			  struct ldmdb *ldb)
{
	int size, perbuf, skip, finish, s, v, recs;
	u8 *data = NULL;
	Sector sect;
	bool result = false;
	LIST_HEAD (frags);

	BUG_ON(!state || !ldb);

	size   = ldb->vm.vblk_size;
	perbuf = 512 / size;
	skip   = ldb->vm.vblk_offset >> 9;		/* Bytes to sectors */
	finish = (size * ldb->vm.last_vblk_seq) >> 9;

	for (s = skip; s < finish; s++) {		/* For each sector */
		data = read_part_sector(state, base + OFF_VMDB + s, &sect);
		if (!data) {
			ldm_crit ("Disk read failed.");
			goto out;
		}

		for (v = 0; v < perbuf; v++, data+=size) {  /* For each vblk */
			if (MAGIC_VBLK != get_unaligned_be32(data)) {
				ldm_error ("Expected to find a VBLK.");
				goto out;
			}

			recs = get_unaligned_be16(data + 0x0E);	/* Number of records */
			if (recs == 1) {
				if (!ldm_ldmdb_add (data, size, ldb))
					goto out;	/* Already logged */
			} else if (recs > 1) {
				if (!ldm_frag_add (data, size, &frags))
					goto out;	/* Already logged */
			}
			/* else Record is not in use, ignore it. */
		}
		put_dev_sector (sect);
		data = NULL;
	}

	result = ldm_frag_commit (&frags, ldb);	/* Failures, already logged */
out:
	if (data)
		put_dev_sector (sect);
	ldm_frag_free (&frags);

	return result;
}