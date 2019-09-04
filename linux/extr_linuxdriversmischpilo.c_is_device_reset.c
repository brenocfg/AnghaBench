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
struct ilo_hwinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device_outbound (struct ilo_hwinfo*) ; 
 int is_db_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_device_reset(struct ilo_hwinfo *hw)
{
	/* check for global reset condition */
	return is_db_reset(get_device_outbound(hw));
}