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
struct vc_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ con_is_visible (struct vc_data const*) ; 
 int /*<<< orphan*/  console_blanked ; 

__attribute__((used)) static inline bool con_should_update(const struct vc_data *vc)
{
	return con_is_visible(vc) && !console_blanked;
}