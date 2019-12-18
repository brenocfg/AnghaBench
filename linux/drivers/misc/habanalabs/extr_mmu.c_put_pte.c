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
struct pgt_info {int num_of_ptes; } ;
struct hl_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_hop (struct hl_ctx*,int /*<<< orphan*/ ) ; 
 struct pgt_info* get_pgt_info (struct hl_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int put_pte(struct hl_ctx *ctx, u64 hop_addr)
{
	struct pgt_info *pgt_info = get_pgt_info(ctx, hop_addr);
	int num_of_ptes_left;

	pgt_info->num_of_ptes--;

	/*
	 * Need to save the number of ptes left because free_hop might free
	 * the pgt_info
	 */
	num_of_ptes_left = pgt_info->num_of_ptes;
	if (!num_of_ptes_left)
		free_hop(ctx, hop_addr);

	return num_of_ptes_left;
}