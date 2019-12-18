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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void target_append_str(char **str, const char *txt)
{
	char *prev = *str;

	*str = *str ? kasprintf(GFP_ATOMIC, "%s,%s", *str, txt) :
		kstrdup(txt, GFP_ATOMIC);
	kfree(prev);
}