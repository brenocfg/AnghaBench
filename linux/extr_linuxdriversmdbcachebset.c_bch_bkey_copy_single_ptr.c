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
typedef  int /*<<< orphan*/  uint64_t ;
struct bkey {int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int KEY_PTRS (struct bkey const*) ; 
 int /*<<< orphan*/  SET_KEY_CSUM (struct bkey*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_KEY_PTRS (struct bkey*,int) ; 
 int /*<<< orphan*/  memcpy (struct bkey*,struct bkey const*,int) ; 

void bch_bkey_copy_single_ptr(struct bkey *dest, const struct bkey *src,
			      unsigned int i)
{
	BUG_ON(i > KEY_PTRS(src));

	/* Only copy the header, key, and one pointer. */
	memcpy(dest, src, 2 * sizeof(uint64_t));
	dest->ptr[0] = src->ptr[i];
	SET_KEY_PTRS(dest, 1);
	/* We didn't copy the checksum so clear that bit. */
	SET_KEY_CSUM(dest, 0);
}