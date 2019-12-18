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
struct mod_hdr_key {int num_actions; int /*<<< orphan*/  actions; } ;

/* Variables and functions */
 int MLX5_MH_ACT_SZ ; 
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 hash_mod_hdr_info(struct mod_hdr_key *key)
{
	return jhash(key->actions,
		     key->num_actions * MLX5_MH_ACT_SZ, 0);
}