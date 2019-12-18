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
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  head ;
typedef  size_t __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  UCLOGIC_RDESC_PH_HEAD 128 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 size_t* kmemdup (size_t const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (size_t*,size_t const*,int) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__u8 *uclogic_rdesc_template_apply(const __u8 *template_ptr,
				   size_t template_size,
				   const s32 *param_list,
				   size_t param_num)
{
	static const __u8 head[] = {UCLOGIC_RDESC_PH_HEAD};
	__u8 *rdesc_ptr;
	__u8 *p;
	s32 v;

	rdesc_ptr = kmemdup(template_ptr, template_size, GFP_KERNEL);
	if (rdesc_ptr == NULL)
		return NULL;

	for (p = rdesc_ptr; p + sizeof(head) < rdesc_ptr + template_size;) {
		if (memcmp(p, head, sizeof(head)) == 0 &&
		    p[sizeof(head)] < param_num) {
			v = param_list[p[sizeof(head)]];
			put_unaligned(cpu_to_le32(v), (s32 *)p);
			p += sizeof(head) + 1;
		} else {
			p++;
		}
	}

	return rdesc_ptr;
}