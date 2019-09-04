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
struct sm3_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM3_BLOCK_SIZE ; 
 int /*<<< orphan*/  sm3_transform (struct sm3_state*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void sm3_generic_block_fn(struct sm3_state *sst, u8 const *src,
				    int blocks)
{
	while (blocks--) {
		sm3_transform(sst, src);
		src += SM3_BLOCK_SIZE;
	}
}