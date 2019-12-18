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
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/  const) ; 
 int snprintf (char*,unsigned int,char*,int,int,int,int) ; 

__attribute__((used)) static int srpt_format_guid(char *buf, unsigned int size, const __be64 *guid)
{
	const __be16 *g = (const __be16 *)guid;

	return snprintf(buf, size, "%04x:%04x:%04x:%04x",
			be16_to_cpu(g[0]), be16_to_cpu(g[1]),
			be16_to_cpu(g[2]), be16_to_cpu(g[3]));
}