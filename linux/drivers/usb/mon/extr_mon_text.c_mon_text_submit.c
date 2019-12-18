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
struct urb {int dummy; } ;
struct mon_reader_text {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  mon_text_event (struct mon_reader_text*,struct urb*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mon_text_submit(void *data, struct urb *urb)
{
	struct mon_reader_text *rp = data;
	mon_text_event(rp, urb, 'S', -EINPROGRESS);
}