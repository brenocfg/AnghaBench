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
struct tun_file {int napi_frags_enabled; } ;

/* Variables and functions */

__attribute__((used)) static bool tun_napi_frags_enabled(const struct tun_file *tfile)
{
	return tfile->napi_frags_enabled;
}