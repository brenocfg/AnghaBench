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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _clear_cam_entry (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_cam_cache (struct adapter*,int /*<<< orphan*/ ) ; 

inline void clear_cam_entry(struct adapter *adapter, u8 id)
{
	_clear_cam_entry(adapter, id);
	clear_cam_cache(adapter, id);
}