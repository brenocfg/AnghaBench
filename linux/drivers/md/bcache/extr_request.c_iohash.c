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
struct hlist_head {int dummy; } ;
struct cached_dev {struct hlist_head* io_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECENT_IO_BITS ; 
 size_t hash_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *iohash(struct cached_dev *dc, uint64_t k)
{
	return &dc->io_hash[hash_64(k, RECENT_IO_BITS)];
}