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
struct st_var_header {int /*<<< orphan*/  var_id; } ;
struct punc_var_t {int /*<<< orphan*/  value; } ;
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct kobj_attribute {TYPE_1__ attr; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct punc_var_t* spk_get_punc_var (int /*<<< orphan*/ ) ; 
 int spk_set_mask_bits (char*,int /*<<< orphan*/ ,int) ; 
 struct st_var_header* spk_var_header_by_name (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static ssize_t punc_store(struct kobject *kobj, struct kobj_attribute *attr,
			  const char *buf, size_t count)
{
	int x;
	struct st_var_header *p_header;
	struct punc_var_t *var;
	char punc_buf[100];
	unsigned long flags;

	x = strlen(buf);
	if (x < 1 || x > 99)
		return -EINVAL;

	p_header = spk_var_header_by_name(attr->attr.name);
	if (!p_header) {
		pr_warn("p_header is null, attr->attr.name is %s\n",
			attr->attr.name);
		return -EINVAL;
	}

	var = spk_get_punc_var(p_header->var_id);
	if (!var) {
		pr_warn("var is null, p_header->var_id is %i\n",
			p_header->var_id);
		return -EINVAL;
	}

	memcpy(punc_buf, buf, x);

	while (x && punc_buf[x - 1] == '\n')
		x--;
	punc_buf[x] = '\0';

	spin_lock_irqsave(&speakup_info.spinlock, flags);

	if (*punc_buf == 'd' || *punc_buf == 'r')
		x = spk_set_mask_bits(NULL, var->value, 3);
	else
		x = spk_set_mask_bits(punc_buf, var->value, 3);

	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	return count;
}