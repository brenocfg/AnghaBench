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
struct usdhi6_host {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  USDHI6_SOFT_RST ; 
 int USDHI6_SOFT_RST_RESERVED ; 
 int USDHI6_SOFT_RST_RESET ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usdhi6_reset(struct usdhi6_host *host)
{
	int i;

	usdhi6_write(host, USDHI6_SOFT_RST, USDHI6_SOFT_RST_RESERVED);
	cpu_relax();
	usdhi6_write(host, USDHI6_SOFT_RST, USDHI6_SOFT_RST_RESERVED | USDHI6_SOFT_RST_RESET);
	for (i = 1000; i; i--)
		if (usdhi6_read(host, USDHI6_SOFT_RST) & USDHI6_SOFT_RST_RESET)
			break;

	return i ? 0 : -ETIMEDOUT;
}