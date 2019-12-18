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
typedef  int /*<<< orphan*/  u16 ;
struct vringh {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio16 ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  vringh16_to_cpu (struct vringh const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int getu16_kern(const struct vringh *vrh,
			      u16 *val, const __virtio16 *p)
{
	*val = vringh16_to_cpu(vrh, READ_ONCE(*p));
	return 0;
}