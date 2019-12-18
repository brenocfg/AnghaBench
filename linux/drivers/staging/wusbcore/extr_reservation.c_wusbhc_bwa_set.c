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
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {int (* bwa_set ) (struct wusbhc*,int /*<<< orphan*/ ,struct uwb_mas_bm const*) ;} ;
struct uwb_mas_bm {int dummy; } ;

/* Variables and functions */
 int stub1 (struct wusbhc*,int /*<<< orphan*/ ,struct uwb_mas_bm const*) ; 
 struct uwb_mas_bm uwb_mas_bm_zero ; 

__attribute__((used)) static int wusbhc_bwa_set(struct wusbhc *wusbhc, u8 stream,
	const struct uwb_mas_bm *mas)
{
	if (mas == NULL)
		mas = &uwb_mas_bm_zero;
	return wusbhc->bwa_set(wusbhc, stream, mas);
}