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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int line_get_config (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char**) ; 
 int /*<<< orphan*/  vts ; 

__attribute__((used)) static int con_get_config(char *dev, char *str, int size, char **error_out)
{
	return line_get_config(dev, vts, ARRAY_SIZE(vts), str, size, error_out);
}