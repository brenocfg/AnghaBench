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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int dummy; } ;
struct fcram_hash_ipv4 {int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 unsigned long FCRAM_SIZE ; 
 int /*<<< orphan*/  HASH_HEADER_EXT ; 
 int hash_write (struct niu*,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fcram_hash_ipv4*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fflp_hash_clear(struct niu *np)
{
	struct fcram_hash_ipv4 ent;
	unsigned long i;

	/* IPV4 hash entry with valid bit clear, rest is don't care.  */
	memset(&ent, 0, sizeof(ent));
	ent.header = HASH_HEADER_EXT;

	for (i = 0; i < FCRAM_SIZE; i += sizeof(ent)) {
		int err = hash_write(np, 0, i, 1, (u64 *) &ent);
		if (err)
			return err;
	}
	return 0;
}