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

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int iscsi_check_for_auth_key(char *key)
{
	/*
	 * RFC 1994
	 */
	if (!strcmp(key, "CHAP_A") || !strcmp(key, "CHAP_I") ||
	    !strcmp(key, "CHAP_C") || !strcmp(key, "CHAP_N") ||
	    !strcmp(key, "CHAP_R"))
		return 1;

	/*
	 * RFC 2945
	 */
	if (!strcmp(key, "SRP_U") || !strcmp(key, "SRP_N") ||
	    !strcmp(key, "SRP_g") || !strcmp(key, "SRP_s") ||
	    !strcmp(key, "SRP_A") || !strcmp(key, "SRP_B") ||
	    !strcmp(key, "SRP_M") || !strcmp(key, "SRP_HM"))
		return 1;

	return 0;
}