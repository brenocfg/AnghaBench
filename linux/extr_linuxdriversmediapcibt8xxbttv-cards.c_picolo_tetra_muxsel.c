#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_GPIO_DATA ; 
 int /*<<< orphan*/  btwrite (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void picolo_tetra_muxsel (struct bttv* btv, unsigned int input)
{

	dprintk("%d : picolo_tetra_muxsel =>  input = %d\n", btv->c.nr, input);
	/*Just set the right path in the analog multiplexers : channel 1 -> 4 ==> Analog Mux ==> MUX0*/
	/*GPIO[20]&GPIO[21] used to choose the right input*/
	btwrite (input<<20,BT848_GPIO_DATA);

}