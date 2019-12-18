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
struct TYPE_2__ {scalar_t__ io_base; } ;

/* Variables and functions */
 int MAX_SOCKETS ; 
 int /*<<< orphan*/  enter (char*) ; 
 unsigned int indirect_read (int,int) ; 
 int /*<<< orphan*/  leave (char*) ; 
 TYPE_1__* sockets ; 

__attribute__((used)) static int card_present(int socketno)
{	
	unsigned int val;
	enter("card_present");
	
	if ((socketno<0) || (socketno >= MAX_SOCKETS))
		return 0;
	if (sockets[socketno].io_base == 0)
		return 0;

		
	val = indirect_read(socketno, 1); /* Interface status register */
	if ((val&12)==12) {
		leave("card_present 1");
		return 1;
	}
		
	leave("card_present 0");
	return 0;
}