__attribute__((used)) static int uPow(int base, int power)
{
	if (power == 0)
		return 1;
	else
		return (base)*uPow(base, power - 1);
}