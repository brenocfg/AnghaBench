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
typedef  int /*<<< orphan*/  u32 ;
struct clip_tbl {int clipt_size; } ;

/* Variables and functions */
 unsigned int jhash_1word (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int ipv4_clip_hash(struct clip_tbl *c, const u32 *key)
{
	unsigned int clipt_size_half = c->clipt_size / 2;

	return jhash_1word(*key, 0) % clipt_size_half;
}