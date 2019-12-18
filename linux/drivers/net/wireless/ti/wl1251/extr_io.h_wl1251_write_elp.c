#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct wl1251 {TYPE_1__* if_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct wl1251*,int,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* write_elp ) (struct wl1251*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wl1251*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wl1251*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void wl1251_write_elp(struct wl1251 *wl, int addr, u32 val)
{
	if (wl->if_ops->write_elp)
		wl->if_ops->write_elp(wl, addr, val);
	else
		wl->if_ops->write(wl, addr, &val, sizeof(u32));
}