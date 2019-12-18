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
struct ef4_nic {int /*<<< orphan*/  biu_lock; } ;
typedef  int /*<<< orphan*/  ef4_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_PAGED_REG (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ef4_writed (struct ef4_nic*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void _ef4_writed_page_locked(struct ef4_nic *efx,
					   const ef4_dword_t *value,
					   unsigned int reg,
					   unsigned int page)
{
	unsigned long flags __attribute__ ((unused));

	if (page == 0) {
		spin_lock_irqsave(&efx->biu_lock, flags);
		ef4_writed(efx, value, EF4_PAGED_REG(page, reg));
		spin_unlock_irqrestore(&efx->biu_lock, flags);
	} else {
		ef4_writed(efx, value, EF4_PAGED_REG(page, reg));
	}
}