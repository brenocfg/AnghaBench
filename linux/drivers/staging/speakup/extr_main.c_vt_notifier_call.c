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
typedef  char u16 ;
struct vt_notifier_param {char c; struct vc_data* vc; } ;
struct vc_data {int /*<<< orphan*/  vc_mode; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KD_TEXT ; 
 int NOTIFY_OK ; 
#define  VT_ALLOCATE 131 
#define  VT_DEALLOCATE 130 
#define  VT_UPDATE 129 
#define  VT_WRITE 128 
 int /*<<< orphan*/  speakup_allocate (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speakup_bs (struct vc_data*) ; 
 int /*<<< orphan*/  speakup_con_update (struct vc_data*) ; 
 int /*<<< orphan*/  speakup_con_write (struct vc_data*,char*,int) ; 
 int /*<<< orphan*/  speakup_deallocate (struct vc_data*) ; 

__attribute__((used)) static int vt_notifier_call(struct notifier_block *nb,
			    unsigned long code, void *_param)
{
	struct vt_notifier_param *param = _param;
	struct vc_data *vc = param->vc;

	switch (code) {
	case VT_ALLOCATE:
		if (vc->vc_mode == KD_TEXT)
			speakup_allocate(vc, GFP_ATOMIC);
		break;
	case VT_DEALLOCATE:
		speakup_deallocate(vc);
		break;
	case VT_WRITE:
		if (param->c == '\b') {
			speakup_bs(vc);
		} else {
			u16 d = param->c;

			speakup_con_write(vc, &d, 1);
		}
		break;
	case VT_UPDATE:
		speakup_con_update(vc);
		break;
	}
	return NOTIFY_OK;
}