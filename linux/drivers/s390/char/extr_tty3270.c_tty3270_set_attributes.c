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
struct tty3270 {int esc_npar; int* esc_par; unsigned char f_color; void* highlight; } ;

/* Variables and functions */
#define  TAC_BLUE 135 
#define  TAC_DEFAULT 134 
#define  TAC_GREEN 133 
#define  TAC_PINK 132 
#define  TAC_RED 131 
 unsigned char TAC_RESET ; 
#define  TAC_TURQ 130 
#define  TAC_WHITE 129 
#define  TAC_YELLOW 128 
 void* TAX_BLINK ; 
 void* TAX_RESET ; 
 void* TAX_REVER ; 
 void* TAX_UNDER ; 

__attribute__((used)) static void
tty3270_set_attributes(struct tty3270 *tp)
{
	static unsigned char f_colors[] = {
		TAC_DEFAULT, TAC_RED, TAC_GREEN, TAC_YELLOW, TAC_BLUE,
		TAC_PINK, TAC_TURQ, TAC_WHITE, 0, TAC_DEFAULT
	};
	int i, attr;

	for (i = 0; i <= tp->esc_npar; i++) {
		attr = tp->esc_par[i];
		switch (attr) {
		case 0:		/* Reset */
			tp->highlight = TAX_RESET;
			tp->f_color = TAC_RESET;
			break;
		/* Highlight. */
		case 4:		/* Start underlining. */
			tp->highlight = TAX_UNDER;
			break;
		case 5:		/* Start blink. */
			tp->highlight = TAX_BLINK;
			break;
		case 7:		/* Start reverse. */
			tp->highlight = TAX_REVER;
			break;
		case 24:	/* End underlining */
			if (tp->highlight == TAX_UNDER)
				tp->highlight = TAX_RESET;
			break;
		case 25:	/* End blink. */
			if (tp->highlight == TAX_BLINK)
				tp->highlight = TAX_RESET;
			break;
		case 27:	/* End reverse. */
			if (tp->highlight == TAX_REVER)
				tp->highlight = TAX_RESET;
			break;
		/* Foreground color. */
		case 30:	/* Black */
		case 31:	/* Red */
		case 32:	/* Green */
		case 33:	/* Yellow */
		case 34:	/* Blue */
		case 35:	/* Magenta */
		case 36:	/* Cyan */
		case 37:	/* White */
		case 39:	/* Black */
			tp->f_color = f_colors[attr - 30];
			break;
		}
	}
}