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
typedef  int u8 ;
struct iwl_trans {int dummy; } ;
struct iwl_tfh_tfd {int /*<<< orphan*/  num_tbs; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 iwl_pcie_gen2_get_num_tbs(struct iwl_trans *trans,
				    struct iwl_tfh_tfd *tfd)
{
	return le16_to_cpu(tfd->num_tbs) & 0x1f;
}