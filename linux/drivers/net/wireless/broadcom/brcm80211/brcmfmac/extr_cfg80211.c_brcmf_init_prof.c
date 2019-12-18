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
struct brcmf_cfg80211_profile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct brcmf_cfg80211_profile*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcmf_init_prof(struct brcmf_cfg80211_profile *prof)
{
	memset(prof, 0, sizeof(*prof));
}