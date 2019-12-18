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
struct tb {int dummy; } ;
struct icm_pkg_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __icm_tr_device_connected (struct tb*,struct icm_pkg_header const*,int) ; 

__attribute__((used)) static void
icm_icl_device_connected(struct tb *tb, const struct icm_pkg_header *hdr)
{
	__icm_tr_device_connected(tb, hdr, true);
}