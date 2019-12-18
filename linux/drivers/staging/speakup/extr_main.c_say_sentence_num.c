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
 int bn ; 
 int currbuf ; 
 int currsentence ; 
 int* numsentences ; 
 scalar_t__* sentbufend ; 
 scalar_t__** sentmarks ; 
 int /*<<< orphan*/  spkup_write (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int say_sentence_num(int num, int prev)
{
	bn = currbuf;
	currsentence = num + 1;
	if (prev && --bn == -1)
		bn = 1;

	if (num > numsentences[bn])
		return 0;

	spkup_write(sentmarks[bn][num], sentbufend[bn] - sentmarks[bn][num]);
	return 1;
}