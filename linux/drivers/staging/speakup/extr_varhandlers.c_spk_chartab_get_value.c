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
 int ALPHA ; 
 int A_CAP ; 
 int A_PUNC ; 
 int B_CAPSYM ; 
 int B_CTL ; 
 int B_SYM ; 
 int NUM ; 
 int PUNC ; 
 int WDLM ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int spk_chartab_get_value(char *keyword)
{
	int value = 0;

	if (!strcmp(keyword, "ALPHA"))
		value = ALPHA;
	else if (!strcmp(keyword, "B_CTL"))
		value = B_CTL;
	else if (!strcmp(keyword, "WDLM"))
		value = WDLM;
	else if (!strcmp(keyword, "A_PUNC"))
		value = A_PUNC;
	else if (!strcmp(keyword, "PUNC"))
		value = PUNC;
	else if (!strcmp(keyword, "NUM"))
		value = NUM;
	else if (!strcmp(keyword, "A_CAP"))
		value = A_CAP;
	else if (!strcmp(keyword, "B_CAPSYM"))
		value = B_CAPSYM;
	else if (!strcmp(keyword, "B_SYM"))
		value = B_SYM;
	return value;
}