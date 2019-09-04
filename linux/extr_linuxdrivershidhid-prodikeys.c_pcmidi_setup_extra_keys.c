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
struct pcmidi_snd {int ifnum; struct input_dev* input_ep82; scalar_t__* last_key; } ;
struct input_dev {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 unsigned int KEY_ADDRESSBOOK ; 
 unsigned int KEY_CALENDAR ; 
 unsigned int KEY_CLOSE ; 
 unsigned int KEY_COFFEE ; 
 unsigned int KEY_DOCUMENTS ; 
 unsigned int KEY_FN ; 
 unsigned int KEY_FORWARDMAIL ; 
 unsigned int KEY_HELP ; 
 unsigned int KEY_MESSENGER ; 
 unsigned int KEY_NEW ; 
 unsigned int KEY_OPEN ; 
 unsigned int KEY_PRINT ; 
 unsigned int KEY_REDO ; 
 unsigned int KEY_REPLY ; 
 unsigned int KEY_SAVE ; 
 unsigned int KEY_SEND ; 
 unsigned int KEY_SPELLCHECK ; 
 unsigned int KEY_SPREADSHEET ; 
 unsigned int KEY_UNDO ; 
 unsigned int KEY_WORDPROCESSOR ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmidi_setup_extra_keys(
	struct pcmidi_snd *pm, struct input_dev *input)
{
	/* reassigned functionality for N/A keys
		MY PICTURES =>	KEY_WORDPROCESSOR
		MY MUSIC=>	KEY_SPREADSHEET
	*/
	unsigned int keys[] = {
		KEY_FN,
		KEY_MESSENGER, KEY_CALENDAR,
		KEY_ADDRESSBOOK, KEY_DOCUMENTS,
		KEY_WORDPROCESSOR,
		KEY_SPREADSHEET,
		KEY_COFFEE,
		KEY_HELP, KEY_SEND,
		KEY_REPLY, KEY_FORWARDMAIL,
		KEY_NEW, KEY_OPEN,
		KEY_CLOSE, KEY_SAVE,
		KEY_UNDO, KEY_REDO,
		KEY_SPELLCHECK,	KEY_PRINT,
		0
	};

	unsigned int *pkeys = &keys[0];
	unsigned short i;

	if (pm->ifnum != 1)  /* only set up ONCE for interace 1 */
		return;

	pm->input_ep82 = input;

	for (i = 0; i < 24; i++)
		pm->last_key[i] = 0;

	while (*pkeys != 0) {
		set_bit(*pkeys, pm->input_ep82->keybit);
		++pkeys;
	}
}