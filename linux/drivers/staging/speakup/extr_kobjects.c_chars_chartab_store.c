#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct kobj_attribute {TYPE_1__ attr; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_DESC_LEN ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_char_chartab_status (int,int,int,int,int) ; 
 unsigned long simple_strtoul (char*,char**,int) ; 
 TYPE_2__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 char** spk_characters ; 
 int* spk_chartab ; 
 int spk_chartab_get_value (char*) ; 
 char** spk_default_chars ; 
 int /*<<< orphan*/  spk_reset_default_chars () ; 
 int /*<<< orphan*/  spk_reset_default_chartab () ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t chars_chartab_store(struct kobject *kobj,
				   struct kobj_attribute *attr,
				   const char *buf, size_t count)
{
	char *cp = (char *)buf;
	char *end = cp + count; /* the null at the end of the buffer */
	char *linefeed = NULL;
	char keyword[MAX_DESC_LEN + 1];
	char *outptr = NULL;	/* Will hold keyword or desc. */
	char *temp = NULL;
	char *desc = NULL;
	ssize_t retval = count;
	unsigned long flags;
	unsigned long index = 0;
	int charclass = 0;
	int received = 0;
	int used = 0;
	int rejected = 0;
	int reset = 0;
	int do_characters = !strcmp(attr->attr.name, "characters");
	size_t desc_length = 0;
	int i;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	while (cp < end) {
		while ((cp < end) && (*cp == ' ' || *cp == '\t'))
			cp++;

		if (cp == end)
			break;
		if ((*cp == '\n') || strchr("dDrR", *cp)) {
			reset = 1;
			break;
		}
		received++;

		linefeed = strchr(cp, '\n');
		if (!linefeed) {
			rejected++;
			break;
		}

		if (!isdigit(*cp)) {
			rejected++;
			cp = linefeed + 1;
			continue;
		}

		/*
		 * Do not replace with kstrtoul:
		 * here we need temp to be updated
		 */
		index = simple_strtoul(cp, &temp, 10);
		if (index > 255) {
			rejected++;
			cp = linefeed + 1;
			continue;
		}

		while ((temp < linefeed) && (*temp == ' ' || *temp == '\t'))
			temp++;

		desc_length = linefeed - temp;
		if (desc_length > MAX_DESC_LEN) {
			rejected++;
			cp = linefeed + 1;
			continue;
		}
		if (do_characters) {
			desc = kmalloc(desc_length + 1, GFP_ATOMIC);
			if (!desc) {
				retval = -ENOMEM;
				reset = 1;	/* just reset on error. */
				break;
			}
			outptr = desc;
		} else {
			outptr = keyword;
		}

		for (i = 0; i < desc_length; i++)
			outptr[i] = temp[i];
		outptr[desc_length] = '\0';

		if (do_characters) {
			if (spk_characters[index] != spk_default_chars[index])
				kfree(spk_characters[index]);
			spk_characters[index] = desc;
			used++;
		} else {
			charclass = spk_chartab_get_value(keyword);
			if (charclass == 0) {
				rejected++;
				cp = linefeed + 1;
				continue;
			}
			if (charclass != spk_chartab[index]) {
				spk_chartab[index] = charclass;
				used++;
			}
		}
		cp = linefeed + 1;
	}

	if (reset) {
		if (do_characters)
			spk_reset_default_chars();
		else
			spk_reset_default_chartab();
	}

	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	report_char_chartab_status(reset, received, used, rejected,
				   do_characters);
	return retval;
}