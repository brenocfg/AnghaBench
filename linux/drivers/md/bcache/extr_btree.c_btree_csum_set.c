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
typedef  int uint64_t ;
struct TYPE_2__ {int* ptr; } ;
struct btree {TYPE_1__ key; } ;
struct bset {int dummy; } ;

/* Variables and functions */
 int bch_crc64_update (int,void*,int) ; 
 void* bset_bkey_last (struct bset*) ; 

__attribute__((used)) static uint64_t btree_csum_set(struct btree *b, struct bset *i)
{
	uint64_t crc = b->key.ptr[0];
	void *data = (void *) i + 8, *end = bset_bkey_last(i);

	crc = bch_crc64_update(crc, data, end - data);
	return crc ^ 0xffffffffffffffffULL;
}