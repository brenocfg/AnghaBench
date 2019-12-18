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
struct nfp_abm {unsigned int num_prios; int /*<<< orphan*/  num_bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  order_base_2 (int /*<<< orphan*/ ) ; 
 unsigned int round_up (unsigned int,int) ; 
 unsigned int roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int nfp_abm_ctrl_prio_map_size(struct nfp_abm *abm)
{
	unsigned int size;

	size = roundup_pow_of_two(order_base_2(abm->num_bands));
	size = DIV_ROUND_UP(size * abm->num_prios, BITS_PER_BYTE);
	size = round_up(size, sizeof(u32));

	return size;
}