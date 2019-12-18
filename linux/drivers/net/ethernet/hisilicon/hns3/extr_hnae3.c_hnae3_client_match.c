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
typedef  enum hnae3_client_type { ____Placeholder_hnae3_client_type } hnae3_client_type ;

/* Variables and functions */
 int HNAE3_CLIENT_KNIC ; 
 int HNAE3_CLIENT_ROCE ; 

__attribute__((used)) static bool hnae3_client_match(enum hnae3_client_type client_type)
{
	if (client_type == HNAE3_CLIENT_KNIC ||
	    client_type == HNAE3_CLIENT_ROCE)
		return true;

	return false;
}