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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ INTEL_GUC_ACTION_DEFAULT ; 
 scalar_t__ ct_header_get_action (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ct_header_is_response(u32 header)
{
	return ct_header_get_action(header) == INTEL_GUC_ACTION_DEFAULT;
}