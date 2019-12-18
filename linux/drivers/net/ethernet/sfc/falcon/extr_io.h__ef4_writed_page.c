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
struct ef4_nic {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_PAGED_REG (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ef4_writed (struct ef4_nic*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
_ef4_writed_page(struct ef4_nic *efx, const ef4_dword_t *value,
		 unsigned int reg, unsigned int page)
{
	ef4_writed(efx, value, EF4_PAGED_REG(page, reg));
}