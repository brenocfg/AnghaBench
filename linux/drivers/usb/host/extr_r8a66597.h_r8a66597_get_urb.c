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
typedef  int /*<<< orphan*/  u16 ;
struct urb {int dummy; } ;
struct r8a66597_td {struct urb* urb; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 struct r8a66597_td* r8a66597_get_td (struct r8a66597*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct urb *r8a66597_get_urb(struct r8a66597 *r8a66597,
					   u16 pipenum)
{
	struct r8a66597_td *td;

	td = r8a66597_get_td(r8a66597, pipenum);
	return (td ? td->urb : NULL);
}