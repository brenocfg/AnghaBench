#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int __u32 ;
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 unsigned int ASC_CONTROL ; 
 size_t ASC_ENABLE ; 
 int ASC_ENABLE_SAMPLE ; 
 size_t ASC_MODE ; 
 int ASC_MODE_SAMPLE ; 
 size_t ASC_VOLUME ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mac_asc_inited ; 
 int* mac_asc_regs ; 
 int* mac_asc_wave_tab ; 
 int /*<<< orphan*/  mac_init_asc () ; 
 int /*<<< orphan*/  mac_nosound (int /*<<< orphan*/ ) ; 
 TYPE_1__ mac_sound_timer ; 
 int /*<<< orphan*/  mac_special_bell (unsigned int,unsigned int,int) ; 

void mac_mksound( unsigned int freq, unsigned int length )
{
	__u32 cfreq = ( freq << 5 ) / 468;
	unsigned long flags;
	int i;

	if ( mac_special_bell == NULL )
	{
		/* Do nothing */
		return;
	}

	if ( !mac_asc_inited )
		mac_init_asc();

	if ( mac_special_bell )
	{
		mac_special_bell( freq, length, 128 );
		return;
	}

	if ( freq < 20 || freq > 20000 || length == 0 )
	{
		mac_nosound( 0 );
		return;
	}

	local_irq_save(flags);

	del_timer( &mac_sound_timer );

	for ( i = 0; i < 0x800; i++ )
		mac_asc_regs[ i ] = 0;
	for ( i = 0; i < 0x800; i++ )
		mac_asc_regs[ i ] = mac_asc_wave_tab[ i ];

	for ( i = 0; i < 8; i++ )
		*( __u32* )( ( __u32 )mac_asc_regs + ASC_CONTROL + 0x814 + 8 * i ) = cfreq;

	mac_asc_regs[ 0x807 ] = 0;
	mac_asc_regs[ ASC_VOLUME ] = 128;
	mac_asc_regs[ 0x805 ] = 0;
	mac_asc_regs[ 0x80F ] = 0;
	mac_asc_regs[ ASC_MODE ] = ASC_MODE_SAMPLE;
	mac_asc_regs[ ASC_ENABLE ] = ASC_ENABLE_SAMPLE;

	mac_sound_timer.expires = jiffies + length;
	add_timer( &mac_sound_timer );

	local_irq_restore(flags);
}