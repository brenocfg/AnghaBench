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
#define  KEY_ADDRESSBOOK 147 
#define  KEY_CALENDAR 146 
#define  KEY_CLOSE 145 
#define  KEY_COFFEE 144 
#define  KEY_DOCUMENTS 143 
#define  KEY_FN 142 
#define  KEY_FORWARDMAIL 141 
#define  KEY_HELP 140 
#define  KEY_MESSENGER 139 
#define  KEY_NEW 138 
#define  KEY_OPEN 137 
#define  KEY_PRINT 136 
#define  KEY_REDO 135 
#define  KEY_REPLY 134 
#define  KEY_SAVE 133 
#define  KEY_SEND 132 
#define  KEY_SPELLCHECK 131 
#define  KEY_SPREADSHEET 130 
#define  KEY_UNDO 129 
#define  KEY_WORDPROCESSOR 128 
 int /*<<< orphan*/  set_bit (unsigned int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmidi_setup_extra_keys(
	struct pcmidi_snd *pm, struct input_dev *input)
{
	/* reassigned functionality for N/A keys
		MY PICTURES =>	KEY_WORDPROCESSOR
		MY MUSIC=>	KEY_SPREADSHEET
	*/
	static const unsigned int keys[] = {
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

	const unsigned int *pkeys = &keys[0];
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