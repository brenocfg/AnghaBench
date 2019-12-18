#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct ath10k {TYPE_2__ hif; } ;
struct TYPE_3__ {int (* map_service_to_pipe ) (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ath10k_hif_map_service_to_pipe(struct ath10k *ar,
						 u16 service_id,
						 u8 *ul_pipe, u8 *dl_pipe)
{
	return ar->hif.ops->map_service_to_pipe(ar, service_id,
						ul_pipe, dl_pipe);
}