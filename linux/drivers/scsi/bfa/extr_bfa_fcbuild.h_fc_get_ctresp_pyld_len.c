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
typedef  scalar_t__ u32 ;
struct ct_hdr_s {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline   u32
fc_get_ctresp_pyld_len(u32 resp_len)
{
	return resp_len - sizeof(struct ct_hdr_s);
}