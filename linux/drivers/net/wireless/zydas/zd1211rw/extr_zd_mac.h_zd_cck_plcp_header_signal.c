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
struct cck_plcp_header {int /*<<< orphan*/  signal; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 zd_cck_plcp_header_signal(const struct cck_plcp_header *header)
{
	return header->signal;
}