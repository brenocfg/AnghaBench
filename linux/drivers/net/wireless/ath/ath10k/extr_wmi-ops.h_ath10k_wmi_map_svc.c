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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct ath10k {TYPE_2__ wmi; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* map_svc ) (int /*<<< orphan*/  const*,unsigned long*,size_t) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,unsigned long*,size_t) ; 

__attribute__((used)) static inline int
ath10k_wmi_map_svc(struct ath10k *ar, const __le32 *in, unsigned long *out,
		   size_t len)
{
	if (!ar->wmi.ops->map_svc)
		return -EOPNOTSUPP;

	ar->wmi.ops->map_svc(in, out, len);
	return 0;
}